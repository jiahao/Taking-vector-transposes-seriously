include("rankstability.jl")
info("Lua/Torch semantics")

#Multiply is *
#Transpose is A:t()

@axiom matmul Mat * Mat --> Mat
@axiom matvec Mat * Vec --> Vec
#"multiplication between 1D and 2D tensors not yet supported"
#@axiom vecmat Vec * Mat --> Mat
@axiom vecvec Vec * Vec --> Scal

# internal error in __mul: no metatable
#@axiom scalvec Scal * Vec --> Vec
@axiom vecscal Vec * Scal --> Vec #ok

#@axiom matdiv Mat / Mat --> Mat
#Only 2 dimensional tensors can be transposed
@axiom mattrans transpose(Mat) --> Mat
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


try
    @show (A*x)', x'*A', (A*x)' == (x'*A')
catch
    info("(A*x)' =/= (x'*A')")
end

println("Axioms used:")
println(join(sort(collect(keys(axiomsused))), "\n"))
println()
