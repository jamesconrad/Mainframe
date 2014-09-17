
class generationclass {
private:
	char * generated;
	int width, height;
	int seed;
public:
	generationclass();
	generationclass(const generationclass&);
	~generationclass();

	int initialize(int, int, int);
	int generate();
	int convertToChar();
};