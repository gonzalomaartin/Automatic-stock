class order : public container{

  private:

    int index = 0;

  public:

    const char* ID;
    container* containers;

    order(int ncont, const char* idorder)
    {
      ID = idorder;
      containers = new container[ncont];
    }

    void add_container(container c_add)
    {
      containers[index] = c_add;
      index++;
    }

};