# Julia test program

# Multiplication: *
# Division: /
# Transpose: '
using Base.Test

m = 5
n = 4
A = ones(m, n)
B = ones(n, m)
C = ones(n, n)

rowmat = ones(1, n)
colmat = ones(m, 1)

x = ones(m)
y = ones(n)
z = ones(n)

α = 1.0
β = 1.0 


# Multiplications
#################

@test size(A*B) === (m, m)

@test size(A*y) === (m,)

@test size(A*α) === (m, n)

@test_throws DimensionMismatch x*A
@test size(x*rowmat) === (m, n)

@test_throws MethodError x*y

@test size(x*α) === (m,)

@test size(α*A) === (m, n)

@test size(α*x) === (m,)

@test size(α*β) === ()


# Divisions
###########

@test size(A/A) === (m, m)

@test_throws DimensionMismatch A/x
@test size(colmat/x) === (m, m)

@test size(A/α) === (m, n)

@test_throws DimensionMismatch x/B
@test size(x/colmat) === (m, m)

@test size(x/x) === (m, m)

@test size(x/α) === (m,)

@test_throws MethodError α/A

@test_throws MethodError α/x

@test size(α/β) === ()


# Transpositions
################

@test size(A') === (n, m)

@test size(x') === (1, m)

@test size(α') === ()


###############
# Expressions #
###############

#Inner
@test size(x'*x) === (1,)

#Outer
@test size(x*y') === (m, n)

#Quadratic
@test size(y'*C*y) === (1,)

#Bilinear
@test size(x'*A*y) === (1,)

#Rayleigh
@test size((y'*C*y)/(y'*y)) === (1,1)



##############
# Identities #
##############

@test x'' != x

@test (A*y)' == (y')*(A')

@test_throws MethodError x*(y'*z) == (x*y')*z
