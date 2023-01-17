open! StdLabels
open! MoreLabels

let count n l r =
  let dp =
    Array.init (n + 1) ~f:(fun _ ->
        Array.init (l + 1) ~f:(fun _ -> Array.init (r + 1) ~f:(fun _ -> 0L)))
  in

  dp.(1).(1).(1) <- 1L;
  for i = 2 to n do
    for j = 1 to l do
      for k = 1 to r do
        dp.(i).(j).(k) <-
          Int64.(
            mul (of_int (i - 2)) dp.(i - 1).(j).(k)
            |> add dp.(i - 1).(j - 1).(k)
            |> add dp.(i - 1).(j).(k - 1)
            |> fun x -> rem x 1000000007L)
      done
    done
  done;

  dp.(n).(l).(r)

let () =
  let n, l, r =
    read_line () |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    |> fun xs -> (List.nth xs 0, List.nth xs 1, List.nth xs 2)
  in
  count n l r |> Int64.to_string |> print_endline
