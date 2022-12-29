type time = {
  hour : int;
  minute : int;
  second : int;
}

let addSeconds curTime s =
  let curSeconds = curTime.hour * 3600 + curTime.minute * 60 + curTime.second in
  let newSeconds = curSeconds + s in
  {
    hour = (newSeconds / 3600) mod 24;
    minute = (newSeconds / 60) mod 60;
    second = newSeconds mod 60;
  }

let () =
  let t = read_line () |> String.split_on_char ' ' |> List.map int_of_string in
  let time = {hour = List.nth t 0; minute = List.nth t 1; second = List.nth t 2} in
  let s = read_int () in
  let newTime = addSeconds time s in
  [newTime.hour; newTime.minute; newTime.second] |> List.map string_of_int |> String.concat " " |> print_endline