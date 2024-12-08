#ifndef ACTION_H
#define ACTION_H 




class Action {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
}


















#endif