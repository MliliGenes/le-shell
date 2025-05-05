const operators = {
    '||': 1,
    '&&': 2,
    '|': 3,
    '(': 0,
    ')': 0
  };
  
  function isOperator(token) {
    return Object.keys(operators).includes(token);
  }
  
  function getPrecedence(op) {
    return operators[op] ?? -1;
  }
  
  function shuntingYard(tokens) {
    const output = [];
    const stack = [];
  
    for (const token of tokens) {
      if (!isOperator(token) && token !== '(' && token !== ')') {
        output.push(token);
      } else if (token === '(') {
        stack.push(token);
      } else if (token === ')') {
        while (stack.length && stack[stack.length - 1] !== '(') {
          output.push(stack.pop());
        }
        stack.pop(); // Pop '('
      } else {
        while (
          stack.length &&
          getPrecedence(stack[stack.length - 1]) >= getPrecedence(token)
        ) {
          output.push(stack.pop());
        }
        stack.push(token);
      }
    }
  
    while (stack.length) {
      output.push(stack.pop());
    }
  
    return output;
  }
  
  function validatePostfix(infixInput, postfixInput) {
    const infixTokens = infixInput.trim().match(/"[^"]*"|\S+/g);
    const postfixTokens = postfixInput.trim().match(/"[^"]*"|\S+/g);
  
    const generatedPostfix = shuntingYard(infixTokens);
  
    const isValid =
      generatedPostfix.length === postfixTokens.length &&
      generatedPostfix.every((val, i) => val === postfixTokens[i]);
  
    if (isValid) {
      console.log('✅ Postfix is correct!');
    } else {
      console.log('❌ Postfix is incorrect.');
      console.log('Expected :', generatedPostfix.join(' '));
      console.log('Provided :', postfixTokens.join(' '));
    }
  }
  
  // Example usage:
  // node validatePostfix.js "ls | \"$grep\" && cat" "ls \"$grep\" | cat &&"
  
  const [infix, postfix] = process.argv.slice(2);
  if (!infix || !postfix) {
    console.log('Usage:\n  node validatePostfix.js "infix" "postfix"');
  } else {
    validatePostfix(infix, postfix);
  }
  