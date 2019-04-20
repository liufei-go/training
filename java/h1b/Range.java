public class Range {

	double _min;
	double _max;
	double _step;

	public Range(double min, double max, double step) {
		_min = min;
		_max = max;
		_step = step;
	}

	public double get_min() {
		return _min;
	}
	public double get_max() {
		return _max;
	}
	public double get_step() {
		return _step;
	}
}