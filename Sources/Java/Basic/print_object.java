// package console;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class print_object {
	static void print(Object obj) {
		if (obj.getClass().isArray()) {
			for (int i = 0; i < Array.getLength(obj); i++) {
				System.out.print(Array.get(obj, i) + " ");
			}
			System.out.println();
		} else {
			System.out.println(obj);
		}
	}

	public static void main(String[] args) {
		// Raw Type
		int[] arr = { 3, 4, 5 };
		print(arr);
		// Box Type
		Integer[] arr_box = { 3, 4, 5 };
		print(arr_box);
		// List Type
		List<Integer> list = new ArrayList<Integer>(Arrays.asList(1, 2, 3, 3));
		/*
		 * If:List list = Arrays.asList(1,2,3,3); list.add is error.
		 */
		list.add(12);
		print(list);
		// Set Type
		Set<Integer> set = new HashSet<Integer>(Arrays.asList(1, 2, 3, 3));
		set.add(12);
		print(set);
	}
}