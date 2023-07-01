class Condition {
private:
    Node* node;     // Pointer to the associated node
    float value;    // Value of the condition

public:
    // Constructor
    Condition(Node* node_to_assign, float value_to_assign) {
        node = node_to_assign;
        value = value_to_assign;
    }

    // Setter and getter for node
    void set_node(Node* node_to_assign) {
        node = node_to_assign;
    }
    Node* get_node() {
        return node;
    }

    // Setter and getter for value
    void set_value(float value_to_assign) {
        value = value_to_assign;
    }
    float get_value() {
        return value;
    }
};
