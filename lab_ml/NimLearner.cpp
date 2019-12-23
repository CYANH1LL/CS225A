/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>
#include <vector>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    //initialization of vertexs
    for (unsigned i = 0; i <= startingTokens; i++) {

        g_.insertVertex("p1-" + std::to_string(i));
        g_.insertVertex("p2-" + std::to_string(i));
        if (i >= 2) {

          Vertex p1 = "p1-" + std::to_string(i);
          Vertex p1_take_1= "p1-" + std::to_string(i - 1);
          Vertex p1_take_2 = "p1-" + std::to_string(i - 2);
          Vertex p2 = "p2-" + std::to_string(i);
          Vertex p2_take_1 = "p2-" + std::to_string(i - 1);
          Vertex p2_take_2 = "p2-" + std::to_string(i - 2);

          g_.insertEdge(p1, p2_take_1);
          g_.setEdgeWeight(p1, p2_take_1, 0);

          g_.insertEdge(p1, p2_take_2);
          g_.setEdgeWeight(p1, p2_take_2, 0);

          g_.insertEdge(p2, p1_take_1);
          g_.setEdgeWeight(p2, p1_take_1, 0);

          g_.insertEdge(p2, p1_take_2);
          g_.setEdgeWeight(p2, p1_take_2, 0);

        } else if (i == 1) {

          g_.insertEdge("p1-1", "p2-0");
          g_.setEdgeWeight("p1-1", "p2-0", 0);
          g_.insertEdge("p2-1", "p1-0");
          g_.setEdgeWeight("p2-1", "p1-0", 0);

        }
    }
    startingVertex_ = "p1-"+std::to_string(startingTokens);

}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
   Vertex curr = startingVertex_;
   while (g_.getAdjacent(curr).size() != 0) {
     std::vector<Vertex> adj_list = g_.getAdjacent(curr);
     int decision = rand() % adj_list.size();
     Vertex next = adj_list[decision];
     path.push_back(g_.getEdge(curr, next));
     curr = next;
   }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 int coef = 1;
 int i = path.size() - 1;
 while (i >= 0) {
   Edge e = path[i];
   int weight = g_.getEdgeWeight(e.source, e.dest);
   g_.setEdgeWeight(e.source, e.dest, weight + coef);
   coef *= -1;
   i--;
 }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
