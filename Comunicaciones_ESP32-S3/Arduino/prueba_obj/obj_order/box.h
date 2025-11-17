class box : public target{

  public:

    const char* ID;
    target pos;

    box(const char* idbox, target position)
    {
      ID = idbox;
      pos = position;
    }

    box()
    {
      ID = "";
      pos = target(0,0,0);
    }

};