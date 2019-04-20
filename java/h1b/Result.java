public class Result {

	double _number;
	double _percent;
	double _oldValue;
	double _newValue;

	public Result(double number, double percent, double oldValue, double newValue) {
		_number = number;
		_percent = percent;
		_oldValue = oldValue;
		_newValue = newValue;
	}

	public double get_number() {
		return _number;
	}

	public double get_percent() {
		return _percent;
	}

	public double get_old_value() {
		return _oldValue;
	}
	
	public double get_new_value() {
		return _newValue;
	}
}