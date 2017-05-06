#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

class Serializable {
public:
    virtual ~Serializable(){}
    virtual void serialize(std::vector<char>&) = 0;
    virtual void deSerialize(std::vector<char>&) = 0;
};

#endif // SERIALIZABLE_H
