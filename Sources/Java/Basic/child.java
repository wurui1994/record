class FatherClass {
	public FatherClass() {
		System.out.println(100);
	}

	public FatherClass(int age) {
		System.out.println(age);
	}
}

class child extends FatherClass {
	public child() {
		// super();
	}

	public child(int c) {
		super(c);
		// System.out.println(1234);
	}

	public static void main(String[] args) {
		new FatherClass();
		new FatherClass(28);
		new child();
		new child(66);
	}
}