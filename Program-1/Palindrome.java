import java.io.*;

/**
 * This program tests whether the palindrome is balanced.
 * @version 1.0 2017-09-13
 * @author Yujin Yoshimura
 */

public class Palindrome {

	// Main function
	public static void main (String[] args) {
		openFile(filename);
		fetchChar();
		// the integer value -1 represents End Of File.
		while(ch != -1){
			concatChar();
			balance((char)ch);
			fetchChar();
		}
	}

	// Opens an input file, with the file name defined within the class.
	// @param String, path of the input file
	public static void openFile (String path) {
		try {
			File input = new File(path);
			FileReader inputreader = new FileReader(input);
			fr = inputreader;
		}
		catch(FileNotFoundException e) {
			printFileError(e);
		}
	}
	
	// Fetches one character at a time from the input file.
	// @param none
	public static void fetchChar () {
		try {
			ch = fr.read();
		}
		catch(IOException e) {
			printIOError(e);
		}
	}
	
	// Balances the palindrome from the input file, by line.
	// @ param char, fetched character to be balanced
	public static void balance (char c) {
		if (c == '\n'){
			printString(line);
			resetLine();
			examineStack();
			balancer.reset();
		}
		else if (c == '(') {
			balancer.push(trash);
		}
		else if (c == ')') {
			trash = balancer.pop();
		}
	}
	
	// Examines whether the palindrome is balanced or not.
	// @param none
	public static void examineStack () {
		if (balancer.isEmpty()) {
			printString(balanced);
		}
		else {
			printString(unbalanced);
		}
	}
	
	// Concatenates the fetched character to be printed.
	// @param none
	public static void concatChar () {
		line += (char)ch;
	}
	
	// Resets the concatenated string for new line.
	// @param none
	public static void resetLine () {
		line = "";
	}

	// Prints a string.
	// @param String, to be printed
	public static void printString (String s) {
		System.out.print(s);
	}
	
	// Prints File Not Found Exception Error.
	// @param FileNotFoundException, an error message
	public static void printFileError (FileNotFoundException e) {
		System.out.println(e);
	}

	// Prints Input/Output Exception Error.
	// @param IOException, an error message
	public static void printIOError (IOException e) {
		System.out.println(e);
	}	
	
	private static String filename = "Input.txt";
	private static String balanced = " is balanced.\n";
	private static String unbalanced = " is not balanced.\n";
	private static FileReader fr;
	private static int ch = 0;
	private static int trash = 0;
	private static String line = "";
	private static MyStack balancer = new MyStack();

}