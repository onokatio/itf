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

def evaluate(exp: Expression) -> Leaf:
    match exp:
        case BinExp(op, left, right):
            l = evaluate(left).value
            r = evaluate(right).value
            match op:
                case '+': return Leaf(l + r)
                case '-': return Leaf(l - r)
                case '*': return Leaf(l * r)
                case '/': return Leaf(l // r)
                case _: raise Exception("Unknown op: " + op)
        case Leaf(value): return exp
        case _: raise Exception("Unknown expression: " + str(exp))

test_exp1: Expression = BinExp('/',
                            BinExp('*', 
                                Leaf(2),
                                BinExp('-', Leaf(5), Leaf(2))),
                            Leaf(4))
test_exp2: Expression = BinExp('*', 
                            BinExp('+', Leaf(1), Leaf(2)),
                            BinExp('+', Leaf(3), Leaf(4)))


print(evaluate(test_exp1))
print(evaluate(test_exp2))