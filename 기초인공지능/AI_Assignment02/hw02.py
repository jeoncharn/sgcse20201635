from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

## Example Agent
class ReflexAgent(Agent):

  def Action(self, gameState):

    move_candidate = gameState.getLegalActions()

    scores = [self.reflex_agent_evaluationFunc(gameState, action) for action in move_candidate]
    bestScore = max(scores)
    Index = [index for index in range(len(scores)) if scores[index] == bestScore]
    get_index = random.choice(Index)

    return move_candidate[get_index]

  def reflex_agent_evaluationFunc(self, currentGameState, action):

    successorGameState = currentGameState.generatePacmanSuccessor(action)
    newPos = successorGameState.getPacmanPosition()
    oldFood = currentGameState.getFood()
    newGhostStates = successorGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

    return successorGameState.getScore()



def scoreEvalFunc(currentGameState):

  return currentGameState.getScore()

class AdversialSearchAgent(Agent):

  def __init__(self, getFunc ='scoreEvalFunc', depth ='2'):
    self.index = 0
    self.evaluationFunction = util.lookup(getFunc, globals())

    self.depth = int(depth)



class MinimaxAgent(AdversialSearchAgent):
  """
    [문제 01] MiniMaxAgent의 Action을 구현하시오.
    (depth와 evaluation function은 위에서 정의한 self.depth and self.evaluationFunction을 사용할 것.)
  """
  def Action(self, gameState):
    ####################### Write Your Code Here ################################
    # getLegalActions 함수를 이용해, 각각 가능한 움직임을 파악하여, 이를 minmax tree 형태로 사용한다.
    # getLegalActions 함수는 가능한 움직임을 list로 return ex) 'East', 'West'
    # 따라서 각 결과에 대해 generateSuccessor 을 적용해 주어야 다음 gameState을 파악할 수 있다.

    """ 첫 구현에서 사용했던 함수
      def max_state(gameState_list):
      eval_data = [self.evaluationFunction(state) for state in gameState_list]
      max_value = max(eval_data)
      max_index = eval_data.index(max_value)

      return gameState_list[max_index]

      def min_state(gameState_list):
      eval_data = [self.evaluationFunction(state) for state in gameState_list]
      min_value = min(eval_data)
      min_index = eval_data.index(min_value)

      return gameState_list[min_index]
    """

    def max_value(gameState, current_depth, current_agent, agentIndex):
      # 정해진 depth 만큼 수행한 경우
      if current_depth == self.depth:
        return (self.evaluationFunction(gameState), 0)
      
      # 가능한 움직임이 존재하지 않는 경우
      if gameState.getLegalActions(current_agent) == []:
        return (self.evaluationFunction(gameState), 0)
      
      v_value = float("-inf")
      move = ""
      for action in gameState.getLegalActions(current_agent):
        v2, _ = min_value(gameState.generateSuccessor(current_agent, action), current_depth, current_agent + 1, agentIndex)
        if v2 > v_value:
          v_value, move = v2, action
      
      return v_value, move
      

    def min_value(gameState, current_depth, current_agent, agentIndex):
      # 정해진 depth 만큼 수행한 경우
      if current_depth == self.depth:
        return (self.evaluationFunction(gameState), 0)
      
      # 가능한 움직임이 존재하지 않는 경우
      if gameState.getLegalActions(current_agent) == []:
        return (self.evaluationFunction(gameState), 0)

      # 마지막 유령이 아닌 경우(2가지 유령 중 첫 번째 유령이다.)
      # 더 많은 유령의 수에서도 Action을 수행할 수 있도록 위와 같이 설정했다.
      if current_agent != agentIndex - 1:
        
        v_value = float("-inf")
        move = ""

        for action in gameState.getLegalActions(current_agent):
          v2, _ = min_value(gameState.generateSuccessor(current_agent, action), current_depth, current_agent + 1, agentIndex)
          if v2 > v_value:
            v_value, move = v2, action

      # 마지막 유령인 경우
      else:
        v_value = float("inf")
        move = ""

        for action in gameState.getLegalActions(current_agent):
          v2, _ = max_value(gameState.generateSuccessor(current_agent, action), current_depth + 1, 0, agentIndex)
          if v2 < v_value:
            v_value, move = v2, action

      return v_value, move

    # minimax_search 로 max value을 갖는 move을 찾아낸다.
    # current_depth은 현재 검색의 깊이
    # current_agent는 현재 pacman, 유령1, 유령2 인지를 파악한다.
    def minimax_search(gameState, current_depth, current_agent, agentIndex = 3):
      
      value, move = max_value(gameState, current_depth, current_agent, agentIndex)
      
      return move
      
    # Action 의 return value
    return minimax_search(gameState, 0, 0)

    """
      첫 구현 하지만 alpha-beta pruning 을 적용할 수 없어 다시 구현해 주었다.

          def recursive_minmax(gameState, current_depth, current_agent, agentIndex = 3):

      # 현재 depth가 self.depth와 동일하면, recursive의 종료조건이 된다.
      if current_depth == self.depth:
        return gameState
      
      # 현재 state에서 더 이상 움직일 수 없는 경우
      if gameState.getLegalActions(current_agent) == []:
        return gameState

      next_gameState_list = []

      #print(gameState.getLegalActions(current_agent))
      # 다음 행동의 List을 구현한다.
      for action in gameState.getLegalActions(current_agent):
        next_gameState_list.append(gameState.generateSuccessor(current_agent, action))
      
      candidate_state = []
      # 첫 번째 agent 인 pacman의 움직임을 파악한다.
      if current_agent == 0:
        for state in next_gameState_list:
          candidate_state.append(recursive_minmax(state, current_depth, current_agent + 1, agentIndex))

        # 첫 번째 agent이며, 첫 번째 depth인 경우, 방향을 return 해 주어야 한다.
        if current_depth == 0:
          return_state = max_state(candidate_state)
          action_index = candidate_state.index(return_state)
          return gameState.getLegalActions(current_agent)[action_index]

        return max_state(candidate_state)

      # 마지막 agent인 경우 (agentIndex = 3 인 경우에, 두 번째 유령을 의미한다.) 
      elif current_agent == agentIndex - 1:
        for state in next_gameState_list:
          candidate_state.append(recursive_minmax(state, current_depth + 1, 0, agentIndex))
        return min_state(candidate_state)

      # 중간 유령인 경우 (agentIndex = 3인 경우에, 첫 번째 유령을 의미한다.) 
      else:
        for state in next_gameState_list:
          candidate_state.append(recursive_minmax(state, current_depth, current_agent + 1, agentIndex))
        return min_state(candidate_state)
    
      #print("current eval value :", self.evaluationFunction(gameState))

      return recursive_minmax(gameState, 0, 0)
    """


    #raise Exception("Not implemented yet")

    ############################################################################



class AlphaBetaAgent(AdversialSearchAgent):
  """
    [문제 02] AlphaBetaAgent의 Action을 구현하시오.
    (depth와 evaluation function은 위에서 정의한 self.depth and self.evaluationFunction을 사용할 것.)
  """
  def Action(self, gameState):
    ####################### Write Your Code Here ################################
    # 각각 current agent, current depth 에 따라 a-b data를 가질 수 있다.
    # ex) 3개의 agent, 4의 depth 라면 3*4 = 12 개의 data 가능

    def max_value(gameState, current_depth, current_agent, alpha, beta, agentIndex):
      if current_depth == self.depth:
        return (self.evaluationFunction(gameState), 0)
      
      if gameState.getLegalActions(current_agent) == []:
        return (self.evaluationFunction(gameState), 0)
      
      v_value = float("-inf")
      move = ""
      for action in gameState.getLegalActions(current_agent):
        v2, _ = min_value(gameState.generateSuccessor(current_agent, action), current_depth, current_agent + 1, alpha, beta, agentIndex)
        if v2 > v_value:
          v_value, move = v2, action
          # alpha 값을 update 한다.
          alpha = max(alpha, v_value)
        # 종료 조건을 추가한다.
        if v_value >= beta:
          return v_value, move
      
      return v_value, move
      

    def min_value(gameState, current_depth, current_agent, alpha, beta, agentIndex):
      if current_depth == self.depth:
        return (self.evaluationFunction(gameState), 0)
      
      if gameState.getLegalActions(current_agent) == []:
        return (self.evaluationFunction(gameState), 0)

      if current_agent != agentIndex - 1:
        
        v_value = float("-inf")
        move = ""

        for action in gameState.getLegalActions(current_agent):
          v2, _ = min_value(gameState.generateSuccessor(current_agent, action), current_depth, current_agent + 1, alpha, beta, agentIndex)
          if v2 > v_value:
            v_value, move = v2, action
            alpha = max(alpha, v_value)
          if v_value >= beta:
            return v_value, move
          

      else:
        v_value = float("inf")
        move = ""

        for action in gameState.getLegalActions(current_agent):
          v2, _ = max_value(gameState.generateSuccessor(current_agent, action), current_depth + 1, 0, alpha, beta, agentIndex)
          if v2 < v_value:
            v_value, move = v2, action
            # 마지막 유령인 경우, beta 값을 update 한다.
            beta = min(beta, v_value)
          # 종료 조건을 추가한다.
          if v_value <= alpha:
            return v_value, move

      return v_value, move

    # 초기 값으로 alpha = 음의 무한대, beta = 양의 무한대를 전달한다.
    def alpha_beta_search(gameState, current_depth, current_agent, alpha, beta, agentIndex = 3):
      
      value, move = max_value(gameState, current_depth, current_agent, alpha, beta, agentIndex)
      
      return move
      
    # Action 의 return value
    return alpha_beta_search(gameState, 0, 0, float("-inf"), float("inf"))
      
    #raise Exception("Not implemented yet")

    ############################################################################



class ExpectimaxAgent(AdversialSearchAgent):
  """
    [문제 03] ExpectimaxAgent의 Action을 구현하시오.
    (depth와 evaluation function은 위에서 정의한 self.depth and self.evaluationFunction을 사용할 것.)
  """
  def Action(self, gameState):
    ####################### Write Your Code Here ################################
    # 각 유령을 chance node로 설정하여 expectimax 을 구현한다.
    # 따라서 max, min 이 아닌, max, chance function을 통해 구현을 수행해야 한다.
    # expect_max는 아래에서 계산된 값의 avg 값을 return 해 준다.

    def max_value(gameState, current_depth, current_agent, agentIndex):
      if current_depth == self.depth:
        return (self.evaluationFunction(gameState), 0)
      
      if gameState.getLegalActions(current_agent) == []:
        return (self.evaluationFunction(gameState), 0)
      
      v_value = float("-inf")
      move = ""
      for action in gameState.getLegalActions(current_agent):
        v2, _ = chance_value(gameState.generateSuccessor(current_agent, action), current_depth, current_agent + 1, agentIndex)
        if v2 > v_value:
          v_value, move = v2, action
      
      return v_value, move
      

    def chance_value(gameState, current_depth, current_agent, agentIndex):
      if current_depth == self.depth:
        return (self.evaluationFunction(gameState), 0)
      
      if gameState.getLegalActions(current_agent) == []:
        return (self.evaluationFunction(gameState), 0)

      sum_value = 0
      action_num = len(gameState.getLegalActions(current_agent))

      if current_agent != agentIndex - 1:
        
        for action in gameState.getLegalActions(current_agent):
          v2, _ = chance_value(gameState.generateSuccessor(current_agent, action), current_depth, current_agent + 1, agentIndex)
          sum_value += v2

      else:

        for action in gameState.getLegalActions(current_agent):
          v2, _ = max_value(gameState.generateSuccessor(current_agent, action), current_depth + 1, 0, agentIndex)
          sum_value += v2

      # expect value을 계산한다. 평균값을 취한다.
      expect_value = sum_value / action_num
      # move는 평균값이기 때문에, return 하지 않아도 된다. 형태상 편의성을 위해 _ 로 return 한다.
      return expect_value, _

    def expectimax_search(gameState, current_depth, current_agent, agentIndex = 3):
      
      value, move = max_value(gameState, current_depth, current_agent, agentIndex)
      
      return move
      
    # Action 의 return value
    return expectimax_search(gameState, 0, 0)
       
    #raise Exception("Not implemented yet")
    ############################################################################
