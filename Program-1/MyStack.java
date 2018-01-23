public class MyStack {

	// Default Constructor
	// @param none
	public MyStack() {
		first = 0;
		last = 0;
		maxStack = MAXSIZE;
		items = new int [MAXSIZE];
	}

	// Constructor with defined stack size
	// @param int, maximum size
	public MyStack (int max) {
		maxStack = max;
		first = 0;
		last = 0;
		items = new int [max];
	}
	
	// Accessor, returns true when the stack is full
	// @param none
	// @return boolean
	public boolean isFull () {
		return (first == maxStack);
	}
	
	// Accessor, returns true when the stack is empty
	// @param none
	// @return boolean
	public boolean isEmpty () {
		return (first == last);
	}
	
	// Mutator, adds an integer to the array
	// @param int, an item to be added
	public void push(int item) {
		if (!isFull()) {
			items[first] = item;
			first++;
		}
		else {
			System.out.println("Tried to insert into full stack.");
		}
	}

	// Mutator, removes an integer from the array
	// @param none
	// @return int
	public int pop() {
		int item = 0;
		if (!isEmpty()) {
			--first;
			item = items[first];
		}
		else {
			System.out.println("Tried to remove from empty stack.");
		}
		return item;
	}

	// Mutator, resets the stack and makes it empty
	// @param none
	public void reset() {
		first = 0;
		last = 0;
	}

	private final int MAXSIZE = 100;
	private int first;
	private int last;
	private int maxStack;
	private int items[];
}