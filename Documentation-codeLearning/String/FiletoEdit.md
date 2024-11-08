# String (Getting Values from comma's ",")
<br/>

## Example:  

Serial CMD sent data: (123, 456, 789)<br/>
**OUTPUT**<br/>
value1: 123<br/>
value2: 456<br/>
value3: 789


### Code
---
```

void setup() {
  Serial.begin(9600);
}

void loop() {
  String inputstring = Serial.readStringUntil('\n');
  inputstring.replace(")", "");  // Remove the Parenthesis if ever theres parethesis
  inputstring.replace("(", "");


  int commaindex1 = inputstring.indexOf(','); 
  int commaindex2 = inputstring.indexOf(',', commaindex1 + 1);

  int value1 = inputstring.substring(0, commaindex1).toInt();
  int value2 = inputstring.substring(commaindex1 + 1, commaindex2).toInt();
  int value3 = inputstring.substring(commaindex2 + 1).toInt();

  Serial.print("Val1:(");
  Serial.print(value1);
  Serial.println(")");
  Serial.print("Val2:(");
  Serial.print(value2);
  Serial.println(")");
  Serial.print("Val3:(");
  Serial.print(value3);
  Serial.println(")");
  delay(3000);
}

```
---

<br/>

## Explaination
<br/>

```
  String inputstring = Serial.readStringUntil('\n');
```
> Serial.readStringUntil('\n') Just reads the string 0 to End and stops then read newline ('\n') if available.<br/>


```
  int commaindex1 = inputstring.indexOf(','); 
  int commaindex2 = inputstring.indexOf(',', commaindex1 + 1);
```

for example: 123, 42, 123<br/>
-----------------^---^ <br/>
-----------------|--- Find commaindex2; (',', commaindex1 + 1) <br/>
-----------------|-----------------------------------------------^ <br/>
-----------------|-----------------------------------------------This thing allows to sweep and read to the right for the character ",". Then save<br/>
-----------------Start Pointer and find ","; Then save Index to commaindex1 <br/>

> the + 1 lets say just tells the thingy to sweep till the end ","<br/>
More visualization
<br/>

## Visuals

Serial.Read(); = 32, 521, 123

> 32, 521, 123<br/>
> ^ // String pointer imagination :0

int commaindex1 = inputstring.indexOf(','); 

> 32, 521, 123 <br/>
> --^ // Found index! save index position to commindex1

int commaindex2 = inputstring.indexOf(',', commaindex1 + 1);

> 32, 521, 123<br/>
> --^++^ // Found index! Save index position to commaindex2<br/>
> --| Sweep more "commaindex + 1" until "," is found
