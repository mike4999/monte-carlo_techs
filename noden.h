#ifndef NODEN_H
#define NODEN_H

#include "nodebase.h"
#include "nodes.h"

template <int width>
class NodeN : public NodeBase
{
public:
    NodeN(int level);
    ~NodeN();

    void add(INodeS *node);
    void add(NodeN *node);
    bool isFull() const;

    INodeS *find(float *r) const;

private:
    void store(NodeBase *node);
    NodeN<width> *last() const;

    NodeBase *_childs[width];
    int _numberOfChilds;
};

template <int width>
NodeN<width>::NodeN(int level) : NodeBase(level), _numberOfChilds(0) {
    for (int i = 0; i < width; ++i) _childs[i] = 0;
}

template <int width>
NodeN<width>::~NodeN() {
    for (int i = 0; i < _numberOfChilds; ++i) delete _childs[i];
}

template <int width>
void NodeN<width>::add(INodeS *node) {
    if (level() > 1) {
        if (_numberOfChilds == 0 || last()->isFull()) store(new NodeN<width>(level() - 1));
        last()->add(node);
    } else {
        store(node);
    }
    _sum += node->sum();
}

template <int width>
void NodeN<width>::add(NodeN *node) {
    store(node);
    _sum += node->sum();
}

template <int width>
bool NodeN<width>::isFull() const {
    if (_numberOfChilds < width) return false;
    if (level() == 1) return true;
    return last()->isFull();
}

template <int width>
INodeS *NodeN<width>::find(float *r) const {
    for (int i = 0; i < _numberOfChilds; ++i) {
        float childSum = _childs[i]->sum();
        if (*r < childSum) {
            if (level() == 1) {
                return static_cast<INodeS *>(_childs[i]);
            } else {
                return static_cast<NodeN<width> *>(_childs[i])->find(r);
            }
        } else {
            *r -= childSum;
        }
    }
    return 0; // should not happen
}

template <int width>
void NodeN<width>::store(NodeBase *node) {
    node->setParent(this);
    _childs[_numberOfChilds++] = node;
}

template <int width>
NodeN<width> *NodeN<width>::last() const {
    return static_cast<NodeN<width> *>(_childs[_numberOfChilds - 1]);
}

#endif // NODEN_H