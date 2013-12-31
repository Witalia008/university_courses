a(); b(); c(); d(); f(); v();
f(){
    a();
    b();
    c();
}
b() {
    a();
}
c() {
    a();
    b();
    v();
}
d() {
    f();
}
a() {
    d();
}
v() {
    a();
}
ab() {
    A = 1;
    print(A,'\n');
}
main() {
    A = 2;
    print(A, '\n');
    ab();
    f();
    return 0
}
