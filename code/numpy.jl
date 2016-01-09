include("rankstability.jl")
info("NumPy semantics")

#In NumPy,
# * is numpy.dot
# ' is (numpy.matrix(...).transpose()
#
# OLD numpy had numpy.matrix which did _not_ compose with numpy.ndarrays, so
# numpy.matrix does not interact with any true vectors.
#
# Quote from PEP 465:
# The result is a strong consensus among both numpy developers and developers
# of downstream packages that numpy.matrix should essentially never be used,
# because of the problems caused by having conflicting duck types for arrays.

@axiom matmul Mat * Mat --> Mat
@axiom mattrans transpose(Mat) --> Mat
@axiom matvec Mat * Vec --> Vec

@axiom vecmat Vec * Mat --> Vec
@axiom vecvec Vec * Vec --> Scal
@axiom vectrans transpose(Vec) --> Vec

@axiom scaldiv Scal / Scal --> Scal

x = Vec()
y = Vec()
A = Mat()

@tryout inner(x, y)
@tryout outer(x, y)
@tryout bilinear(x, A, y)
@tryout rayleigh(A, x)
@show x'', x'' == x
@show (A*x)', x'*A', (A*x)' == (x'*A')

println("Axioms used:")
println(join(sort(collect(keys(axiomsused))), "\n"))
println()
