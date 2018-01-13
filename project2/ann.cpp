//Brandon Smith
//CSCI 580
//Fall 2016
//Project 2
//ann.cpp

#include"ann.h"

/*
 * Constructor
 */
Ann::Ann(vector<vector<long double> > &w,
    vector<vector<long double> > &in,
    vector<vector<long double> > &in_class,
    vector<long double> &o,
    vector<long double> &o_class,
    vector<int> &nodes,
    int& k, int& l): 
  weights(w), input(in), c_in(in_class),
  c_out(o_class),
  output_class(o), structure(nodes),
  alpha(0.01),
  iter(k), layers(l)  
{
  //Get total number of nodes
  num_nodes = 0;
  for(int i = 0; i < (int)structure.size(); i++)
  {
    num_nodes += structure[i];
  }

  //Set sizes for vectors
  a.resize(num_nodes + 1);
  inp.resize(num_nodes + 1);
  error.resize(num_nodes + 1);
  y.resize(structure.back());
  digits.resize(c_out.size());
  c_in.resize(output_class.size());
  out_train.resize(output_class.size());

  //Run classification of output
  output_classification();
}

/*
 * Runs the neural network on the data set
 * Updates weights, classifies the testing input
 * and calculates accuracy
 */
void Ann::run()
{
  update_weights();
  display_weights();
  input_classification();
  calculate_accuracy();
}

/*
 * Calculates accuracy based on classified digits and supplied output
 */
void Ann::calculate_accuracy()
{
  long double sum = 0;
  long double accuracy = 0;

  //Keep running sum for correct classifications
  for(int i = 0; i < (int)c_out.size(); i++)
  {
    if(digits.at(i) == c_out.at(i))
    {
      sum++;
    }
  }
  accuracy = sum/(long double)c_out.size();
  cout << showpoint << fixed << setprecision(12)
        << accuracy << endl;
}

/*
 * Takes supplied input and classifies it as a digit
 * Compares this classification to the accuracy vector
 * which is based on the testing data set using the
 * Euclidiean distance between the two
 */
void Ann::input_classification()
{
  //Variables
  int temp = 0;
  int temp2 = 0;
  long double sum = 0;    
  long double distance = 0;     //Euclidean distance
  long double min_distance = 0; //Minimum euclidean distance

  //For each outputs
  for(int i = 0; i < (int)c_out.size(); i++)
  {  
    //Initialize a vector based on current input
    for(int j = 0; j < structure[0]; j++)
    {
      a.at(j + 1) = c_in.at(i).at(j); 
    }
    temp = structure[0] + 1;
    temp2 = 1;

    //Run for each layers starting at the first hidden layer
    for(int j = 1; j < layers; j++)
    {
      //Run for each node at that layer
      for(int k = 0; k < structure[j]; k++)
      {
        //Calculate inp for dummy weight
        inp.at(k + temp - 1) = weights.at(0).at(k + temp - 1);
        for(int l = 0; l < structure.at(j-1); l++)
        {
          inp.at(k + temp - 1) += a.at(l + temp2) * weights.at(l + temp2).at(k);
        }

        //Calculate a for this node
        a.at(k + temp) = (long double)1/(long double)(1 + exp(-inp.at(k + temp - 1)));
      }
      temp2 += structure.at(j-1);
      temp += structure.at(j);
    }

    //Set up y equal to back node's a value
    for(int j = 0; j < structure.back(); j++)
    {
      y.at(j) = a.at(j + temp2);
    }

    //Now check the euclidean distance of the output
    for(int k = 0; k < structure.back(); k ++)
    {
      sum = 0;
      for(int j = 0; j < structure.back(); j++)
      {
        //Calculate sum of powers
        sum += pow((output.at(k).at(j) - y.at(j)), 2);
      }
      distance = sqrt(sum);

      //The first distance calculated is the min distance
      if(k == 0)
      {
        min_distance = distance;
        digits.at(i) = k;
      }

      //Otherwise update min_distance
      if(distance < min_distance)
      {
        min_distance = distance;
        digits.at(i) = k;
      }
    }
  }

  //Print out classified digits
  for(int j = 0; j < (int)digits.size(); j++)
  {
    cout << digits.at(j) << endl;
  }
}

/*
 * Takes digit output and transforms it into 
 * vector table corresponding to the same digit
 */
void Ann::output_classification()
{
  //Create classification
  vector<long double> temp;
  for(int i = 0; i < 10; i++)
  {
    output.push_back(temp);
    output[i].push_back(0.9);
    output[i].push_back(0.9);
    output[i].push_back(0.9);
    output[i].push_back(0.9);
    output[i].push_back(0.9);
    output[i].push_back(0.9);
    output[i].push_back(0.9);
    output[i].push_back(0.9);
    output[i].push_back(0.9);
    output[i].push_back(0.9);
    output[i].at(i) =  0.1;
  }
  
  //Classify training output
  for(int i = 0; i < (int)output_class.size(); i++)
  {
    out_train.at(i) = output[output_class[i]];
  }
}

/*
 * Displays the weights attached to the first
 * input layer node for the ann
 */
void Ann::display_weights()
{
  //Print out every weight
  for(int j = 0; j < (int)weights[1].size(); j++)
  {
    cout << showpoint << fixed << setprecision(12)
      << weights[1][j] << " ";
  }
  cout << endl;
}

/*
 * Updates weights for neural network
 */
void Ann::update_weights()
{
  //Variables
  int temp = 0;
  int temp2 = 0;
  int lnodes = 0;       //index of currently layer's nodes
  int pnodes = 0;       //index of next or previous layer's nodes
  long double sum = 0;  //running sum

  //===================Step 1===============
  //Run each test data set Z iterations
  for(int i = 0; i < iter; i++)
  {
    //For each training data set
    for(int z = 0; z < (int)input.size(); z++)
    {
      //Initialize the a matrix from the provided input
      for(int j = 0; j < structure[0]; j++)
      {
        a.at(j + 1) = input.at(z).at(j); 
      }

      //===================Step 2===============
      temp = structure[0] + 1;
      temp2 = 1;

      //For each layer
      for(int j = 1; j < layers; j++)
      {
        //===================Step 3===============
        //For each node in that layer
        for(int k = 0; k < structure.at(j); k++)
        {
          //initialize inp with dummy weights
          inp.at(k + temp) = weights.at(0).at(k + temp - 1);
          for(int l = 0; l < structure.at(j-1); l++)
          {
            inp.at(k + temp) += a.at(l + temp2) * weights.at(l + temp2).at(k);
          }
          //Calculate a at that node
          a.at(k + temp) = (long double)1/(long double)(1 + exp(-1 * inp.at(k + temp)));
        }
        temp2 += structure.at(j-1);
        temp += structure.at(j);
      }

      //===================Step 4==================
      //Get the first node of the layer before the last
      lnodes = num_nodes - structure.back() + 1;

      //For each node in the output layer calculate the error
      for(int j = 0; j < structure.back(); j++)
      {
        error.at(lnodes + j) = a.at(lnodes + j) * (1 - a.at(lnodes + j)) * (out_train.at(z).at(j) - a.at(lnodes + j));
      }

      //===================Step 5==================
      temp2 = num_nodes - structure.at(layers - 1) + 1;
      temp = num_nodes + 1;

      for(int j = 0; j < layers - 1; j++)
      {
        //Get number of nodes from that layer
        lnodes = structure.at(layers - j - 2);     //Layer's nodes (current)
        pnodes = structure.at(layers - j - 1);     //Previous layer's nodes

        //Decrement index for previous and current layers
        temp2 -= lnodes;
        temp -= pnodes; 

        //===================Step 6===============
        //for each node at the current layer
        for(int k = 0; k < lnodes; k++)
        {
          sum = 0;
          //for each node at the previous layer
          for(int m = 0; m < pnodes; m++)
          {
            sum += error.at(temp + m) * weights.at(temp2 + k).at(m);
          }

          //calculate the error at that node
          error.at(temp2 + k) = (a.at(temp2 + k)*(1 - a.at(temp2 + k))) * sum;
        }
      }

      //===================Step 7===============
      lnodes = 1;
      pnodes = structure[0] + 1;

      //Update dummy weights
      for(int k = 0; k < (int)weights[0].size(); k++)
      {
        weights.at(0).at(k) += alpha * error.at(k + 1); 
      }

      //Update all other weights
      for(int k = 0; k < layers - 1; k++)
      {
        for(int j = 0; j < structure[k]; j++)
        {
          //Compute actual weights
          for(int m = 0; m < structure[k + 1]; m++)
          {
            weights.at(lnodes + j).at(m) += alpha * a.at(lnodes + j) * error.at(pnodes + m);
          }
        }
        lnodes += structure.at(k);     //Get index of current node
        pnodes += structure.at(k + 1); //Get index of next layer
      }
    }
  }
}


