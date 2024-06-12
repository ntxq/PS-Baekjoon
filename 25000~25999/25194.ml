open! StdLabels
open! MoreLabels

let find_friday works =
  let rec loop works dp =
    match works with
    | [] -> dp.(4)
    | work :: rest ->
      let new_dp = Array.copy dp in
      for i = 0 to 6 do
        new_dp.((i + work) mod 7) <- dp.(i) || dp.((i + work) mod 7)
      done;
      loop rest new_dp
  in
  let dp = Array.make 7 false in
  dp.(0) <- true;
  loop works dp
;;

let () =
  let _ = input_line stdin in
  let works =
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  in
  if find_friday works then output_string stdout "YES\n" else output_string stdout "NO\n"
;;
