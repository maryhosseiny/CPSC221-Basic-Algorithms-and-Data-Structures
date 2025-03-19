/**
 * @file quack.cpp
 * Implementation of the Quack class.
 *
 */

template <class T>
Quack<T>::Quack() {
    /**
     * @todo Your code here!
     */
     n1 = 0;
     n2 = -1;
}

/**
 * Adds the parameter object to the right of the Quack.
 *
 * @param newItem object to be added to the Quack.
 */
template <class T>
void Quack<T>::pushR(T newItem) {
    n2 = n2+1;
    data.push_back(newItem);
}

/**
 * Removes the object at the left of the Quack, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Quack.
 */
template <class T>
T Quack<T>::popL() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    T item = peekL();
    data.pop_back();
    n1 = n1 + 1;
    if (isEmpty()) {
        n1 = 0;
        n2 = -1;
        data.resize(0);
        return item;
    } 
    if (n2-n1+1 <= n1) {
        vector<T> vector;
        for (int i = n1; i <= n2; i++) {
            vector.push_back(data[i]);
        }
        data.resize(vector.size());
        for (unsigned long i = 0; i < vector.size(); i++) {
            data[i] = vector[i];
        }
        n1 = 0;
        n2 = vector.size()-1;
        return item;
    } 
    return item; 
    
}
/**
 * Removes the object at the right of the Quack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Quack.
 */
template <class T>
T Quack<T>::popR() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    T item = peekR();
    data.pop_back();
    n2 = n2 - 1;
    if (n2-n1+1 <= n1) {
        vector<T> vector;
        for (int i = n1; i <= n2; i++) {
            vector.push_back(data[i]);
        }
        data.resize(vector.size());
        for (unsigned long i = 0; i < vector.size(); i++) {
            data[i] = vector[i];
        }
        n1 = 0;
        n2 = vector.size()-1;
    }
    return item;   
}

/**
 * Finds the object at the left of the Quack, and returns it to the
 * caller. Unlike popL(), this operation does not alter the quack.
 *
 * @return The item at the front of the quack.
 */
template <class T>
T Quack<T>::peekL() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return data[n1];
}

/**
 * Finds the object at the right of the Quack, and returns it to the
 * caller. Unlike popR(), this operation does not alter the quack.
 *
 * @return the value of The item at the right of the quack.
 */
template <class T>
T Quack<T>::peekR() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return data[n2];
}

/**
 * Determines if the Quack is empty.
 *
 * @return bool which is true if the Quack is empty, false otherwise.
 */
template <class T>
bool Quack<T>::isEmpty() const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return (n2 < n1);
}
