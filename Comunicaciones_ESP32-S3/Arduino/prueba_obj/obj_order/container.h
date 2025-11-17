class container : public box{

  private:

    int index = 0;

  public:

    const char* ID;
    box* boxes;

    container(int nbox, const char* idcontainer)
    {
      ID = idcontainer;
      boxes = new box[nbox];
    } 

    container()
    {
      ID = "";
    }

    void add_box(box b_add)
    {
      boxes[index] = b_add;
      index++;
    }
};