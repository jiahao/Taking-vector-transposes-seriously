include("rankstability.jl")
info("Python 3.5/NumPy semantics")

#In NumPy,
# * is Python's @ operator for matmul
# ' is (numpy.matrix(...).transpose()

#Python's @ for matmul is discussed in PEP 465
#http://legacy.python.org/dev/peps/pep-0465/
#
#Quote:
#
#1d vector inputs are promoted to 2d by prepending or appending a '1' to the
#shape, the operation is performed, and then the added dimension is removed
#from the output. The 1 is always added on the "outside" of the shape:
#prepended for left arguments, and appended for right arguments. The result is
#that matrix @ vector and vector @ matrix are both legal (assuming compatible
#shapes), and both return 1d vectors; vector @ vector returns a scalar.

@axiom scalvec Scal * Vec --> Vec
@axiom vecscal Vec * Scal --> Vec

@axiom matmul Mat * Mat --> Mat
@axiom matvec Mat * Vec --> Vec
#@axiom matdiv Mat / Mat --> Mat

@axiom vecmat Vec * Mat --> Vec
@axiom vecvec Vec * Vec --> Scal
@axiom vectrans transpose(Vec) --> Vec

@axiom scaldiv Scal / Scal --> Scal

x = Vec()
y = Vec()
z = Vec()
A = Mat()

@tryout inner(x, y)
@tryout outer(x, y)
@tryout bilinear(x, A, y)
@tryout rayleigh(A, x)
@tryout outact(x, y, z)
@show x'', x'' == x
@show (A*x)', x'*A', (A*x)' == (x'*A')

println("Axioms used:")
println(join(sort(collect(keys(axiomsused))), "\n"))
println()
