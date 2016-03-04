-- Lua test
require 'torch'

m = 5
n = 4

A = torch.ones(m, n)
B = torch.ones(n, m)
C = torch.ones(m, m)
Scal = torch.ones(1, 1)

x = torch.ones(m)
y = torch.ones(n)
z = torch.ones(n)

alpha = 1.0
beta = 1.0



---------------------------
-- Elementary operations --
---------------------------

-- Multiplications
------------------

matmul = A*B
assert(matmul:nDimension() == 2)
assert(matmul:size(1) == m)
assert(matmul:size(2) == m)

-- matscalmul = Scal*A
-- error:
-- size mismatch, m1: [1 x 1], m2: [5 x 4]
-- scalmatmul = A*Scal
-- error:
-- size mismatch, m1: [5 x 4], m2: [1 x 1]
matvec = A*y
assert(matvec:nDimension() == 1)
assert(matvec:size(1) == m)
-- assert(matvec:size(2) == 1)
-- error:
-- bad argument #1 to 'size' (dimension 2 out of range of 1D tensor
-- no trailing singleton dimensions

matscal = A*alpha
assert(matscal:nDimension() == 2)
assert(matscal:size(1) == m)
assert(matscal:size(2) == n)

--vecmat = x*A
--Result: error
--multiplication between 1D and 2D tensors not yet supported

vecvec = x*x
-- Result: print(vecvec:size()) - a scalar

--vecscal = x*alpha

--scalmat = alpha*A
--Result: error
--internal error in __mul: no metatable

--scalvec = alpha*x
--Result: error
--internal error in __mul: no metatable

scalscal = alpha*beta


-- Divisions
------------

-- matmatdiv = A/A
-- Result: error
-- bad argument #2 to '?' (number expected

-- matvecdiv = A/x
-- Result: error
-- bad argument #2 to '?' (number expected

matscaldiv = A/alpha
assert(matscaldiv:nDimension() == 2)
assert(matscaldiv:size(1) == A:size(1))
assert(matscaldiv:size(2) == A:size(2))

-- vecmatdiv = x/A
-- Result: error
-- bad argument #2 to '?' (number expected

--vecvecdiv = x/x
-- Result: error
-- bad argument #2 to '?' (number expected

vecscaldiv = x/alpha
assert(vecscaldiv:nDimension() == 1)
assert(vecscaldiv:size(1) == x:size(1))

-- scalmatdiv = alpha/A
-- Result: error
--  internal error in __div: no metatable

-- scalvecdiv = alpha/x
-- Result: error
--  internal error in __div: no metatable

scalscaldiv = alpha/beta
-- Result: scalar

-- Transpositions
-----------------

mattrans = A:t()
assert(mattrans:nDimension() == 2)
assert(mattrans:size(1) == A:size(2))
assert(mattrans:size(2) == A:size(1))

--vectrans = x:t()
--Result: error
--calling 't' on bad self (Tensor must have 2 dimensions)

--scaltrans = alpha:t()
--Result: error
-- attempt to index global 'alpha' (a number value)



-----------------
-- Expressions --
-----------------

--inner = x:t()*x
--Result: error
--calling 't' on bad self (Tensor must have 2 dimensions)
inner = x:dot(x)

--outer = x*y:t()
--Result: error
--calling 't' on bad self (Tensor must have 2 dimensions)
outer = torch.ger(x, y)

--quadratic = x:t()*C*x
--Result: error
--calling 't' on bad self (Tensor must have 2 dimensions)
quadratic = x:dot(C*x)

--bilinear = x:t()*A*y
--Result: error
--calling 't' on bad self (Tensor must have 2 dimensions)
bilinear = x:dot(A*y)

--rayleigh = x:t()*C*x/(x:t()*x)
--Result: error
--calling 't' on bad self (Tensor must have 2 dimensions)
rayleigh = x:dot(C*x)/(x:dot(x))



----------------
-- Identities --
----------------

--assert( (x:t()):t() == x)
--Result: error
--calling 't' on bad self (Tensor must have 2 dimensions)

--assert( (A*y):t() == y:t() * A:t() )
--Result: error
--calling 't' on bad self (Tensor must have 2 dimensions)

--assert( (x*y:t())*z == x*(y:t()*z) )
--Result: error
--calling 't' on bad self (Tensor must have 2 dimensions)

