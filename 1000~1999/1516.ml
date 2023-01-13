open! StdLabels
open! MoreLabels

let topologySort adj =
  let visited = Array.make (Array.length adj) false in
  let ans = Stack.create () in

  let rec dfs u =
    visited.(u) <- true;
    List.iter adj.(u) ~f:(fun v -> if not visited.(v) then dfs v);
    Stack.push u ans
  in

  for u = 0 to Array.length adj - 1 do
    if not visited.(u) then dfs u
  done;
  ans

let findBuildTimes adj weights =
  let times = Array.make (Array.length adj) 0 in
  let order = topologySort adj in

  Stack.iter
    (fun u ->
      List.iter adj.(u) ~f:(fun v ->
          if times.(v) < times.(u) + weights.(v) then
            times.(v) <- times.(u) + weights.(v)))
    order;
  times

let () =
  let n = read_int () in
  let adj = Array.make (n + 1) [] in
  let weights = Array.make (n + 1) 0 in

  for v = 1 to n do
    let line =
      read_line () |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    in
    weights.(v) <- List.hd line;
    List.iter (List.tl line) ~f:(fun u ->
        if u <> -1 then adj.(u) <- v :: adj.(u) else adj.(0) <- v :: adj.(0))
  done;
  findBuildTimes adj weights |> Array.to_list |> List.tl
  |> List.map ~f:string_of_int |> List.iter ~f:print_endline
