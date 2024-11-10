#!/bin/bash

count_text_stats(){
	input_text="$1"
	char_count=$(echo -n "$input_text" | wc -m)
	word_count=$(echo "$input_text" | wc -w)
	space_count=$(echo "$input_text" | tr -cd ' ' | wc -c)
	special_count=$(echo "$input_text" | tr -cd '[:punct]' | wc -c)

	echo "Text Analysis Report:"; echo " ";
	echo "Character count: $char_count"
	echo "Word count: $word_count"
	echo "Whitespace count: $space_count"
	echo "Special symbol count: $special_count"; echo " ";
}
text_to_analyze="This is an example text! It contains special symbols, such as @ and #."

count_text_stats "$text_to_analyze"

echo "Script execution completd"
