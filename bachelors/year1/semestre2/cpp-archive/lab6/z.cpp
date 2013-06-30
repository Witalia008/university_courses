f1();
f2();
main(){
    Z = if (2 < 5) {
        print(1,'\n');
        break 5;
        print(2,'\n');
    };
    print(Z,'\n');
    first_val = "Hello, ";
    second_val = "World!";
    first_val = first_val + second_val;
    print(first_val,'\n');
    third_val = 39;
    f1();
    second_val = third_val;
    f2();
    print(second_val,'\n');
    return 0;
}
f1(){
    func_val = 201+(704-(3+5)+8)/2+71;
    print(func_val,'\n');
    f2();
}
f2(){
    new = "In f2\n";
    print(new);
}
