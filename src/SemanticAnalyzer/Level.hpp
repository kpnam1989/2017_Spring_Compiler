
//Complete the Level definition and other methods required if any
struct Level {

public :
  Level *upperLevel;
  std::set<Level*> lowerLevels;
  int value;
};
