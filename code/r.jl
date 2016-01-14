include("rankstability.jl")
info("R semantics")

@axiom matvec Mat * Vec --> Mat
@axiom matdiv Mat / Mat --> Mat
@axiom mattrans transpose(Mat) --> Mat

@axiom vecmat Vec * Mat --> Mat
@axiom vectrans transpose(Vec) --> Mat

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
