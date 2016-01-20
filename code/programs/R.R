
# Multiplication operator: %*%

m1 = 5
n1 = 4
m2 = n1
n2 = 2

A = matrix(1.0, m1, n1)
B = matrix(1.0, m2, n2)
C = matrix(1.0, m1, m1)
stopifnot(dim(A) == c(m1, n1))

M1= matrix(1.0, 1, 1)

rowmat = matrix(1.0, 1, n1)
colmat = matrix(1.0, n1, 1)

x = rep(1.0, m1)
y = rep(1.0, n1)
z = rep(1.0, n1)

v1= 1.0

#Note that dim doesn't work on R vectors
stopifnot(dim(x) == NULL)

#no true scalars
stopifnot(identical(1.0, rep(1.0, 1)))

##############################
# Test elementary operations #
##############################

# Multiplication
################

# Matmul
########

A = matrix(1.0, m1, n1)
B = matrix(1.0, m2, n2)
M1= matrix(1.0, 1, 1)

matmul = A%*%B
stopifnot(dim(matmul) == c(m1, n2))

#These are all products with non-conformable arguments
#matrix(1.0, m1, 1)%*% B
#matrix(1.0, n1, 1)%*% B
#matrix(1.0, m2, 1)%*% B
#matrix(1.0, 1, n1)%*%M1
#A%*%M1
#M1%*%A


# Matvec
########

A = matrix(1.0, m1, n1)
y = matrix(1.0, n1)
v1= 1.0

matvec = A%*%y
stopifnot(dim(matvec) == c(m1, 1))

#These are all products with non-conformable arguments
#matrix(1.0, 1, m1)%*%y
#matrix(1.0, m1, 1)%*%y
#M1%*%y

#This is a matrix-scalar product
matvec = A*v1
stopifnot(dim(matvec) == c(m1, n1))



# Vecmat
########

B = matrix(1.0, m2, n2)
x = rep(1.0, m2)

#This is the vector-matrix product
#(ordinary case)
vecmat = x%*%B
stopifnot(dim(vecmat) == c(1, n2))

#This is the outer product
vecmat = x%*%matrix(1.0, 1, n2)
stopifnot(dim(vecmat) == c(m2, n2))

vecmat = 1.0*B
stopifnot(dim(vecmat) == c(m2, n2))



# Vecvec
########

x = rep(1.0, m1)
y = rep(1.0, m2)

#Performs the dot product

#Non-conformable:
#x%*%y
#x%*%1.0

vecvec = x%*%x
stopifnot(dim(vecvec) == c(1, 1))

#...except when the first operand is length 1
vecvec = 1.0*x
stopifnot(dim(vecvec) == c(1, m1))



# (Elementwise) division
########################

vecvecdiv = x/x
stopifnot(length(vecvecdiv) == m1)

# Transposition
###############

mattrans = t(A)
stopifnot(dim(mattrans) == c(n1, m1))

vectrans = t(x)
stopifnot(dim(vectrans) == c(1, m1))



###############
# Expressions #
###############

inner = t(x)%*%x
stopifnot(dim(inner) == c(1,1))

outer = x%*%t(y)
stopifnot(dim(outer) == c(m1,n1))

quadratic = t(x)%*%C%*%x
stopifnot(dim(quadratic) == c(1,1))

bilinear = t(x)%*%A%*%y
stopifnot(dim(bilinear) == c(1,1))

rayleigh = quadratic/(t(x)%*%x)
stopifnot(dim(rayleigh) == c(1,1))



##############
# Identities #
##############

stopifnot(t(t(x)) == x)
#stopifnot(identical(t(t(x)), x))
#FALSE

stopifnot(identical(t(A%*%y), t(y)%*%t(A)))

stopifnot(identical((x%*%t(y))%*%z, x%*%(t(y)%*%z)))


