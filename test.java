// scanner in main with empty string

import java.util.Scanner;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner("4 WE");
		int x = sc.nextInt();
		String s = sc.next();
		System.out.println(x);
		System.out.println(s);
		
	}
}