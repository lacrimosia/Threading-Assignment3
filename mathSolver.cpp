/*-------------------------------------------------------------------------*
 *---                 ---*
 *---   mathSolver.cpp            ---*
 *---                 ---*
 *---     This file defines the high-level functions of the math  ---*
 *--- generator and solver program.         ---*
 *---                 ---*
 *--- ----  ----  ----  ----  ----  ----  ----  ----  ---*
 *---                 ---*
 *--- Version 1a    2019 May 6    Joseph Phillips ---*
 *---                 ---*
 *-------------------------------------------------------------------------*/

//
//  Compile with:
//  $ g++ mathSolver.cpp -o mathSolver -lpthread -g
//

// Shatilla Prayer
// Assignment 3

#include    "./mathSolverHeader.h"

void* evaluate(void* vPtr)
{
    NodeBuffer* nodeBufferPtr = (NodeBuffer*)vPtr;

    // the node pointer variable
    Node* nodePtr;

    //  YOUR CODE HERE
    int probs = NUM_PROBLEMS / 2;
    for(int i = 0;  i < probs;  i++){
        nodePtr = nodeBufferPtr->pullOut();

        // print value
        printf("Iteration num: %d \n",i);
        printf("Node expression: %s \n",nodePtr->toString().c_str());
        printf("Node eval: %g \n",nodePtr->eval());

        // delete pointer
        delete nodePtr;
    }
    return(NULL);
}

//  PURPOSE:  To return a randomly generated Node.
Node* makeNode()
{
    return ((rand() % 3) ? (Node*)new ConstNode() : (Node*)new OperatorNode());
}

int main(int argc,
    char* argv[])
{
    NodeBuffer nodeBuffer;
    pthread_t consumer0;
    pthread_t consumer1;
    int toReturn = EXIT_SUCCESS;

    srand((argc < 2) ? getpid() : atoi(argv[1]));

    //  YOUR CODE HERE
    // Created child threads
    pthread_create(&consumer0,NULL,evaluate,(void*)&nodeBuffer);
    pthread_create(&consumer1,NULL,evaluate,(void*)&nodeBuffer);

    // run node NUM_PROBLEMS times
    for(int i=0; i<NUM_PROBLEMS; i++){
        //make the nodes up until NUM_PROBLEMS
        // Put the return address into node buffers
        Node* ptr = makeNode();
        nodeBuffer.putIn(ptr);
    }

    // wait until they finish
    pthread_join(consumer0, NULL);
    pthread_join(consumer1, NULL);

    return (toReturn);
}
