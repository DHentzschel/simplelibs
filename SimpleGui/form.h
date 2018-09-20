#ifndef FORM_H
#define FORM_H

class FormPrivate;

class Form {
public:
    Form();

    ~Form();

    void setPosition(int x, int y);

    void setSize(int x, int y);

    void show();

private:
    FormPrivate* private_;


};

#endif // FORM_H
