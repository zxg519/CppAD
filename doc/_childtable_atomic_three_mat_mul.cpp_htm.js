// Child table for section atomic_three_mat_mul.cpp
document.write('\
<select onchange="atomic_three_mat_mul__46__cpp_child(this)">\
<option>atomic_three_mat_mul.cpp-&gt;</option>\
<option>atomic_three_mat_mul.hpp</option>\
</select>\
');
function atomic_three_mat_mul__46__cpp_child(item)
{	var child_list = [
		'atomic_three_mat_mul.hpp.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}