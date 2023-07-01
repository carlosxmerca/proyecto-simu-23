class Element {
private:
    int ID;             // ID of the element
    Node* node1;        // Pointer to the first node
    Node* node2;        // Pointer to the second node
    Node* node3;        // Pointer to the third node
    Node* node4;        // Pointer to the fourth node

public:
    // Constructor
    Element(int identifier, Node* first_node, Node* second_node, Node* third_node, Node* fourth_node) {
        ID = identifier;
        node1 = first_node;
        node2 = second_node;
        node3 = third_node;
        node4 = fourth_node;
    }

    // Setter and getter for ID
    void set_ID(int identifier) {
        ID = identifier;
    }
    int get_ID() {
        return ID;
    }

    // Setter and getter for node1
    void set_node1(Node* node) {
        node1 = node;
    }
    Node* get_node1() {
        return node1;
    }

    // Setter and getter for node2
    void set_node2(Node* node) {
        node2 = node;
    }
    Node* get_node2() {
        return node2;
    }

    // Setter and getter for node3
    void set_node3(Node* node) {
        node3 = node;
    }
    Node* get_node3() {
        return node3;
    }

    // Setter and getter for node4
    void set_node4(Node* node) {
        node4 = node;
    }
    Node* get_node4() {
        return node4;
    }
};
