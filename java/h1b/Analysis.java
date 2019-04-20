import java.io.*;
import java.util.*;

public class Analysis {
	public static void main(String[] args) {
		double number = 0;
		double percent = 0;

		final Range NUM_RANGE = new Range(170000, 240000, 5000);
		final Range PER_RANGE = new Range(20, 50, 2);

		final double NUM_A = 20000;
		final double NUM_B = 65000;

		double n = 0;
		double p = 0;

		Vector<Result> vector = new Vector<Result>();

		int counter = 1;
		for (number = NUM_RANGE.get_min(); number <= NUM_RANGE.get_max();)
		{
			for (percent = PER_RANGE.get_min(); percent <= PER_RANGE.get_max();)
			{
				n = number;
				p = percent / 100;

				// Old
				double result1 = (NUM_B * n * p + NUM_A * n - NUM_A * NUM_B) 
					/ (n * p * (n - NUM_A));

				// New
				double result2 = (NUM_A * n + NUM_B * n * p - NUM_B * NUM_B * p - NUM_A * NUM_B)
					/ (n * n * p - NUM_B * n * p);

				/*
				result1 *= 100;
				result2 *= 100;

				System.out.println(counter + " : "+ format(result1) + "  " 
					+ format(result2) + "  " 
					+ format(result2 - result1));
				*/
				vector.addElement(new Result(n, p, result1, result2));

				percent += PER_RANGE.get_step();
				++counter;
			}
			number += NUM_RANGE.get_step();
		}

		PrintWriter out = null;
		try {
			out = new PrintWriter(new File("result.csv"));

			StringBuilder sb = new StringBuilder();
			double row = 0;

			for (int i = 0; i < vector.size(); ++i)
			{
				Result r = vector.get(i);
				if (r.get_number() != row)
				{
					sb.append('\n');
					out.write(sb.toString());

					sb = new StringBuilder();
					row = r.get_number();
					sb.append(r.get_number());
					sb.append(',');
					sb.append((r.get_new_value() - r.get_old_value())*100);
				}
				else
				{
					sb.append(',');
					sb.append((r.get_new_value() - r.get_old_value())*100);
				}

				/*
				sb.append(r.get_number());
				sb.append(',');
				sb.append(r.get_percent());
				sb.append(',');
				sb.append(r.get_new_value() - r.get_old_value());
				sb.append('\n');
				*/
				
			}
			out.close();
		}
		catch (FileNotFoundException e) {
      		System.out.println(e.getMessage());
    	}
	}

	private static String format(double number)
	{
		return String.format("%.2f", number) + "%";
	}
}