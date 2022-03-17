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

@dataclass
class Var(Expression):
    v: str

Environment = dict[str,Leaf]   # 環境の型を定義

def evaluate(exp: Expression, env: Environment) -> Leaf:
    match exp:
        case BinExp(op, left, right):
            l = evaluate(left, env).value
            r = evaluate(right, env).value
            match op:
                case '+': return Leaf(l + r)
                case '-': return Leaf(l - r)
                case '*': return Leaf(l * r)
                case '/': return Leaf(l // r)
                case _: raise Exception("Unknown op: " + op)
        case Leaf(value): return exp
        case Var(v): return env[v]
        case _: raise Exception("Unknown expression: " + str(exp))

class Statement:
    pass

@dataclass
class If(Statement):
    e: Expression
    s1: Statement
    s2: Statement

@dataclass
class While(Statement):
    e: Expression
    s: Statement

@dataclass
class Assign(Statement):
    v: str
    e: Expression

@dataclass
class Sequence(Statement):
    e: list[Expression]

def execute(st: Statement, env: Environment) -> Environment:
    match st:
        case If(e, s1, s2):
            if evaluate(e, env).value != 0:
                return execute(s1, env)
            else:
                return execute(s2, env)
        case While(e, s):
            # 再帰的に実現しても、ループで実現してもよい
            while evaluate(e, env).value != 0:
                env = execute(s, env)
            return env
        case Assign(v, e):
            value = evaluate(e, env)
            env[v] = value
            return env
        case Sequence(e):
            for i in e:
                env = execute(i,env)
            return env
        case _:
            raise Exception("Unknown statement: " + str(st))

#test_st1 = While(Var('i'), 
#              Assign('i', BinExp('-', Var('i'), Leaf(1))))

test_st2 = Sequence([Assign('i', Leaf(10)),
                    Assign('sum', Leaf(0)),
                    While(
                        Var('i'),
                        Sequence(
                            [
                                Assign('sum', BinExp('+', Var('sum'), Var('i'))),
                                Assign('i', BinExp('-', Var('i'), Leaf(1)))
                            ]
                        )
                    )
                    ])

#print(execute(test_st1, {'i': Leaf(10)}))
print(execute(test_st2, {'i': Leaf(10)}))