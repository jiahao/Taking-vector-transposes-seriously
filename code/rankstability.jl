immutable Qty{N} end

typealias Scal Qty{0}
typealias Vec Qty{1}
typealias Mat Qty{2}

######################
# Fundamental axioms #

import Base: *, /, transpose
axiomsused = Dict()

macro axiom(name, expr)
    #expr looks like :(Mat * Mat --> Mat)
    @assert expr.head == :(-->)
    @assert expr.args[1].head == :call

    funcname = expr.args[1].args[1]
    nargs = length(expr.args[1].args) - 1
    axiomname = string(name)
    axiomout = expr.args[end]

    if nargs == 1
        output = quote
            global $funcname
            function $funcname(x::$(expr.args[1].args[2]))
                axiomsused[$axiomname] = get(axiomsused, $axiomname, 0) + 1
                $axiomout()
            end
        end
    elseif nargs == 2
        output = quote
            global $funcname
            function $funcname(x::$(expr.args[1].args[2]), y::$(expr.args[1].args[3]))
                axiomsused[$axiomname] = get(axiomsused, $axiomname, 0) + 1
                $axiomout()
            end
        end
    else
        error("Not implemented")
    end

    argtypes = expr.args[1].args[2:end]
    sigs = join(map(string, argtypes), ", ")
    info("Defining $axiomname: $funcname($sigs) --> $axiomout")
    output
end

@axiom matmul Mat * Mat --> Mat
@assert Mat() * Mat() == Mat()
######################
# Derived operations #

inner(x, y) = x'y
outer(x, y) = x*y'
function bilinear(x, A, y)
    z = (x'*A)*y
    if z == x'*(A*y)
        return z
    else
        error("Not associative")
    end
end
rayleigh(A, x) = x'A*x/x'x
#Action of x*y' on z
function outact(x, y, z)
    w = (x*y')*z
    if w == x*(y'*z)
         return w
    else
        error("Not associative")
    end
end
 
macro tryout(expr)
    output = quote
        try
            println($(esc(expr)), " --> ", typeof($expr))
        catch exc
            println($(esc(expr)), " --> ", exc)#typeof($expr))
            #println(_EXPR, " is a $exc")
        end
    end
    #Now replace _EXPR with the actual expression
    output.args[end].args[1].args[2].args[2] =
    output.args[end].args[end].args[end].args[2] = string(expr)

    output
end
