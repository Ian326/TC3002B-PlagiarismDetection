public class TestCFG {
    public static int sum(int a, int b) {
        return a + b;
    }
    public static void main(String[] args) {
        // Lets make a switch statement
        int x = 1;
        switch (x) {
            case 1:
                System.out.println("x is 1");
                System.out.println("Sum: " + sum(1, 2));
                break;
            case 2:
                System.out.println("x is 2");
                System.out.println("Sum: " + sum(2, 3));
                break;
            default:
                System.out.println("x is not 1 or 2");
                System.out.println("Sum: " + sum(0, 0));
        }
        int y = 2;
    }
}
