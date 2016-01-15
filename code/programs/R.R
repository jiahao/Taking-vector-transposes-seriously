
# Multiplication operator: %*%

n = 4

A = matrix(1.0, n, n)
B = matrix(1.0, n, n)
stopifnot(dim(A) == c(n, n))

rowmat = matrix(1.0, 1, n)
colmat = matrix(1.0, n, 1)

x = rep(1.0, n)
y = rep(1.0, n)
z = rep(1.0, n)

#Note that dim doesn't work on R vectors
stopifnot(dim(x) == NULL)

#no true scalars
stopifnot(identical(1.0, rep(1.0, 1)))

##############################
# Test elementary operations #
##############################

# Multiplication
################

matmul = A%*%B
stopifnot(dim(matmul) == c(n, n))

matvec = A%*%x
stopifnot(dim(matvec) == c(n, 1))

vecmat = x%*%A
stopifnot(dim(vecmat) == c(1, n))

#Performs the dot product
vecvec = x%*%y
stopifnot(dim(vecvec) == c(1, 1))

# (Elementwise) division
########################

vecvecdiv = x/y
stopifnot(length(vecvecdiv) == n)

# Transposition
###############

mattrans = t(A)
stopifnot(dim(mattrans) == c(n, n))

vectrans = t(x)
stopifnot(dim(vectrans) == c(1, n))



###############
# Expressions #
###############

inner = t(x)%*%y
stopifnot(dim(inner) == c(1,1))

outer = x%*%t(y)
stopifnot(dim(outer) == c(n,n))

quadratic = t(x)%*%A%*%x
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

stopifnot(identical(t(A%*%x), t(x)%*%t(A)))

stopifnot(identical((x%*%t(y))%*%z, x%*%(t(y)%*%z)))


