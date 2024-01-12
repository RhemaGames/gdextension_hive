extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	#print($HIVE_WALLET.get_private_key(0))
	#print($HIVE_WALLET.get_private_key(1))
	#print($HIVE_WALLET.get_private_key(2))
	
	$HIVE.get_profile("bflanagin",true)
	$HIVE.get_history("bflanagin",-1,1,true)
	$HIVE.get_blog_history("bflanagin",0,1)
	#$HIVE.call_deferred("get_blog_entry","bflanagin",336)
	
	pass # Replace with function body.
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	pass



func _on_hive_error(type, data):
	var box = $RichTextLabel
	box.append_text("from Error")
	box.append_text(str(type))
	box.append_text(" ")
	box.append_text(str(data)+"\n")
	


func _on_hive_recieved_profile(json):
	var box = $TabContainer/Profile/VBoxContainer/RichTextLabel
	box.append_text("\nFrom recieved profile\n")
	if json["recieved"].has("result"):
		box.append_text(str(json["recieved"]["result"]))	
	


func _on_hive_recieved_history(json):
	var box =  $TabContainer/History/VBoxContainer/RichTextLabel
	box.append_text("\nFrom recieved history\n")
	#box.append_text(str(json["recieved"]["result"]["history"]))
	if json["recieved"].has("result"):
		for p in json["recieved"]["result"]["history"]:
			box.append_text("\n"+str(p))


func _on_hive_recieved_blog_history(json):
	var box =  $TabContainer/Blog/VBoxContainer/RichTextLabel
	box.append_text("\nFrom recieved blog history\n")
	if json["recieved"].has("result"):
		for p in json["recieved"]["result"]:
			box.append_text("\n"+str(p))


func _on_hive_recieved_blog_entry(json):
	print("Blog entry")
	#var box =  $TabContainer/Blog/VBoxContainer/RichTextLabel
	#box.append_text("\nFrom recieved blog history\n")
	#box.append_text(str(json))
	print(str(json))
