from dataclasses import dataclass

class Expression:
    pass

@dataclass
class BinExp(Expression):
    op: str
    left: Expression
    right: Expression

@dataclass
class Leaf(Expression):
    value: int

def step(exp: Expression) -> Expression:
    match exp:
        case BinExp(op, Leaf(l), Leaf(r)):
            match op:
                case '+': return Leaf(l + r)
                case '-': return Leaf(l - r)
                case '*': return Leaf(l * r)
                case '/': return Leaf(l // r)
                case _: raise Exception("Unknown op: " + op)
        case BinExp(op, BinExp(_, _, _) as left, right):
            return BinExp(op, step(left), right)
        case BinExp(op, Leaf(_) as left, BinExp(_, _, _) as right):
            return BinExp(op, left, step(right))
        case _: raise Exception("No applicable rule for: " + str(exp))

def rewrite_loop(exp: Expression) -> Leaf:
    while not isinstance(exp, Leaf):
        exp = step(exp)
    return exp

test_exp1: Expression = BinExp('/',
                            BinExp('*', 
                                Leaf(2),
                                BinExp('-', Leaf(5), Leaf(2))),
                            Leaf(4))
test_exp2: Expression = BinExp('*', 
                            BinExp('+', Leaf(1), Leaf(2)),
                            BinExp('+', Leaf(3), Leaf(4)))


print(rewrite_loop(test_exp1))
print(rewrite_loop(test_exp2))