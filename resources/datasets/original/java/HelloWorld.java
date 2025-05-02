public class HelloWorld {
    public static void main(String[] args) {
        int i = 0;
        if (i == 0) {
            System.out.println("Hello, World!");
            if (i == 0) {
            System.out.println("Hello, World!");
            } else {
                System.out.println("Goodbye, World!");
                
            }
        } else {
            System.out.println("Goodbye, World!");
            
        }
        System.out.println("This is a test.");
        for (int j = 0; j < 5; j++) {
            System.out.println("Loop iteration: " + j);
        }
        while (i < 5) {
            System.out.println("While loop iteration: " + i);
            i++;
        }
        do {
            System.out.println("Do-while loop iteration: " + i);
            i++;
        } while (i < 10);
        
    }
}