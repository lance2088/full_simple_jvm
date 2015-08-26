
class Foo {
    public static void main(String args[]){
        int x = 5;
        int y = 10;
        int c = 0;
        int d = 2;
        System.out.println("HelloWorld");
        c = x+y;
        d +=c ;
        System.out.println(x+ " + " + y + " = " + c);
        c = x*y;
        d +=c ;
        System.out.println(x+ " * " + y + " = " + c);
        c = x-y;
        d +=c ;
        System.out.println(x+ " - " + y + " = " + c);
        c = x/y;
        d +=c ;
        System.out.println(x+ " / " + y + " = " + c);

        System.out.println("d = " + (x+y) + " + " + (x*y) + " + " + (x-y) + " + " + (x/y) + " = " + d );
        System.out.println("Foo Test By WJY");
    }
}
