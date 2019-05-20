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

#include    "./mathSolverHeader.h"

void* evaluate(void* vPtr)
{
    NodeBuffer* nodeBufferPtr = (NodeBuffer*)vPtr;

    //  YOUR CODE HERE
    for(int i = 0;  i < NUM_PROBLEMS / 2;  i++){
        nodeBufferPtr->pullOut();

        // print value
        printf("number %d \n",nodePtr->toString().c_str());
        printf("Node value %d \n",nodePtr->eval());

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
    pthread_mutex_t lock;
    int toReturn = EXIT_SUCCESS;

    srand((argc < 2) ? getpid() : atoi(argv[1]));

    //  YOUR CODE HERE
    // Created child threads
    pthread_mutex_init(&lock,NULL);
    pthread_create(&consumer0,NULL,evaluate,(void*)&nodeBuffer);
    pthread_create(&consumer1,NULL,evaluate,(void*)&nodeBuffer);

    // run node NUM_PROBLEMS times
    for(int i=0; i<NUM_PROBLEMS; i++){
        //make the nodes up until NUM_PROBLEMS
        makeNode();
        // Put the return address into node buffers
        nodeBuffer->putIn(&makeNode());
    }

    // wait until they finish
    void *intPtr;
    pthread_join(&consumer0, (void **)&intPtr);

    void *intPtr2;
    pthread_join(&consumer1, (void **)&intPtr2);

    pthread_mutex_destroy(&lock);

    return (toReturn);
}
