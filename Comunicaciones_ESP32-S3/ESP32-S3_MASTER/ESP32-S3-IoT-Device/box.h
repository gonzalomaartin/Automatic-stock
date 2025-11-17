class box {

  private:

    String ID;
    String pos;
    bool set = false;
    bool pick = false;
    bool place = false;

  public:

    box(String idbox, String position)
    {
      ID = idbox;
      pos = position;
    }

    box()
    {
      ID = "";
      pos = "(0,0,0)";
    }

    String get_boxID()
    {
      return ID;
    }

    String get_boxpos()
    {
      return pos;
    }

    bool get_setBox()
    {
      return set;
    }

    bool get_pickBox()
    {
      return pick;
    }

    bool get_placeBox()
    {
      return place;
    }

    void set_box()
    {
      set = true;
    }

    void pick_box()
    {
      pick = true;
    }

    void place_box()
    {
      place = true;
    }

    void print_box()
    {
      Serial.print("BOX --> ");
      Serial.print(ID);
      Serial.print("; POSE --> ");
      Serial.print(pos);
    }

};