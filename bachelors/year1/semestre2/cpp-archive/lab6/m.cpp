ab(x){
    print("asd\n");
    print(1);
    print('\n');
    print(x+1,'\n');
    return x;
}
ba(c,d);
ba(c,d){
    if (c + d < 10) {
        ba(c + 1, d + 1);
        print('\n',c+d,'\n','\n');
    };
}
main() {
    scan(h);
    h += 5;
    print(h,"\n");
    first_str = "Hello World";
    print(first_str,'\n');

    second_str = " and have a nice day!";
    print(second_str, '\n');

    first_str = first_str * second_str;
    print(first_str, '\n');

    oper_a = (459-2310);
    print(oper_a, '\n');
    a = b = 1;
    a += b;
    print(a+b,'\n');
    ab(a);
    ab(b);
    ba(a+1,b+5);
    oper_b = (459-2310)- 27-(1687-(2571-789));
    print(oper_b, '\n');
    print(ab(a),'\n');

    Y = if (2 + 2 == 4) {
        a = (2 + 2 != 5) ? 2 : 4;
        return 0;
        print('o', '\n');
    } else {
        a = "hello";
    };
    X = for (a = 1, b = 10;if (2 != 3) { a != b };a++) {
        print(1);
    };
    print ('\n', ++X, '\n' );
    Y = while (X--){
        print(2);
    };
    {};
    print('\n',Y, '\n',a,'\n');
    print(Y, ' ',X,'\n');
    res = oper_a-- - ++oper_b;
    print(res, '\n', ("hello", 1, 2 + 2), '\n');
    print(oper_a++ + ++oper_b,'\n');
    print(x : 'a' to 'z', '\n');
    return 0
}
