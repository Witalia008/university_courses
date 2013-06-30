ab();
ab(a){
    print(a,' ');
    if (a <= 5) {
        ab(a + 1);
    } else {
        print('\n');
    };
    return 1
}
main(){
    print(x : 1 to 5,'\n');
    X = for (a = 1, b = 10;if (2 != 3) { a != b };a++) {
        print(1);
    };
    print ('\n', X, '\n' );
    Y = while (--X){
        print(2);
        --X;
    };
    do {
        print(3);
    } while(--Y);
    {};
    print('\n',Y, '\n',a,'\n');
    print(X,'\n');
    print(ab(1),'\n');
    print(x : 'a' to 'z', '\n');
    return 0
}
