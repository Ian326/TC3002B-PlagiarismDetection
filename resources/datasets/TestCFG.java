public class TestCFG {
    public static int sum(int a, int b) {
        return a + b;
    }
    public static void main(String[] args) {
        try {
            int a = 5;
            int b = 10;
            int c = a + b;
            System.out.println("Sum: " + c);
        } catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        } finally {
            System.out.println("Finally block executed");
        }
        int result = sum(3, 4);
    }
}
