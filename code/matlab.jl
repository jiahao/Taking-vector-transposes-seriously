include("rankstability.jl")
info("MATLAB semantics")

@axiom matmul Mat * Mat --> Mat
@axiom mattrans transpose(Mat) --> Mat
@axiom matdiv Mat / Mat --> Mat

x = Mat()
y = Mat()
z = Mat()
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

