include("rankstability.jl")
info("Mathematica semantics")

#Mathematica's Dot and Transpose functions

@axiom matmul Mat * Mat --> Mat
@axiom mattrans transpose(Mat) --> Mat
@axiom matdiv Mat / Mat --> Mat
@axiom scaldiv Scal / Scal --> Scal

@axiom vecvec Vec * Vec --> Scal
@axiom matvec Mat * Vec --> Vec
@axiom vecmat Vec * Mat --> Vec
#@axiom vectrans Transpose[{a, b, c}] is an error

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
