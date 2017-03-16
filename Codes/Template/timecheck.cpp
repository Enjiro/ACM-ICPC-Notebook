using namespace std::chrono;
class timecheck
{
public:
	high_resolution_clock::time_point t1, t2;
	void start()
	{
		t1 = high_resolution_clock::now();
	}
	void end()
	{
		t2= high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		cout << "Time: " << time_span.count() << "s" << endl;
	}
};