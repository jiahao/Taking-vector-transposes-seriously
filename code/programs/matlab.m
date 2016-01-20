m1 = 6;
n1 = 5;
m2 = n1;
n2 = 4;

A = ones(m1, n1);
B = ones(m2, n2);

x = ones(1, m1);
y = ones(n1, 1);

alpha = ones(1);

assert(all(size(A*B) == [m1, n2]));
assert(all(size(alpha*A) == [m1, n1]));
assert(all(size(A*alpha) == [m1, n1]));

